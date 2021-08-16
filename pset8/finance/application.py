import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")



def getUnique(li, key):
    output = set()
    for rows in li:
        output.add(rows[key])
    return output

@app.route("/")
@login_required
def index():
    user = session.get("user_id")
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
    cash = cash[0]['cash']
    stocklist = db.execute("SELECT * FROM transactions WHERE id = ? ORDER BY ticker", user)
    tickers = getUnique(stocklist, "ticker")
    final_list = []
    iterr = 0
    for symbols in tickers:
        final_list.append({"ticker"  : symbols})
        shares = 0
        for items in stocklist:
            if (items["ticker"] == symbols):
                if(items["type"] == "BUY"):
                    shares += items["shares"]
                else:
                    shares -= items["shares"]
        price = lookup(symbols)["price"]
        final_list[iterr].update({"shares" : shares, "price" : price, "value" : price * shares})
        if final_list[iterr]["shares"] == 0:
            final_list.pop(iterr)
            iterr -= 1
        iterr += 1
    iterr  = 0
    totalvalue = cash
    for items in final_list:
        totalvalue += items["value"]



    return render_template("index.html", stocklist = final_list, cash = cash, totalvalue = totalvalue)

    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if (request.method == "GET"):
        return render_template("buy.html", identifier = session.get("user_id"))
    if (request.method == "POST"):
        stock = request.form.get("symbol")
        shares = request.form.get("shares")
        if stock == "" or lookup(stock) == None:
            return apology("ENTER A VALID STOCK", 500)
        shares= int(shares)
        if type(shares) != int or shares < 1:
            return apology("ENTER VALID NUMBER", 500)

        info = lookup(stock)
        price = int(info["price"])
        person = int(session.get("user_id"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?" , person)
        cash = cash[0]['cash']
        if shares * price > cash:
            return apology("not enough cash")
        totalprice = shares * price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - totalprice, person)
        db.execute("INSERT INTO transactions (id, ticker, shares, time, type, pricePerShare) VALUES (?, ?, ?, ?, 'BUY', ?)", person, stock, shares, datetime.now(), price)
        return render_template("bought.html")


    """Buy shares of stock"""
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    user = session.get("user_id")
    stocklist = db.execute("SELECT * FROM transactions WHERE id = ? ORDER BY time DESC", user)
    return render_template("history.html", stocklist = stocklist)
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if (request.method == "POST"):
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("enter a valid symbol", 500)
        return render_template("quotefound.html", quote=quote)
    if (request.method == "GET"):
        return render_template("quotesearch.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if (request.method == "GET"):
        return render_template("register.html")
    else:
        if not request.form.get("username"):
            return apology("must provide username:", 403)
        if not request.form.get("password"):
            return apology("must provide password:", 403)
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match:", 403)
        if len(db.execute("SELECT username FROM users WHERE username = :name", name = request.form.get("username"))) > 0:
            return apology("username taken:", 403)
        else:
            uname = request.form.get("username")
            phash = generate_password_hash(request.form.get("password"))
            db.execute("INSERT INTO users (username, hash) VALUES (:uname, :phash)", uname = uname, phash = phash)
            return redirect("/login")
    return apology("SOEMTHIGN WORNGSNOO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    if request.method == "POST":
        ticker = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user = session.get("user_id")
        totalshares = 0
        sharelist = db.execute("SELECT * FROM transactions WHERE id = ?", user)
        if ticker == None or shares == None:
            return apology("enter valid data")
        for rows in sharelist:
            if rows["type"] == "BUY":
                totalshares += rows['shares']
            else:
                totalshares -= rows['shares']
        if totalshares < shares:
            return apology("not enough shares")
        info = lookup(ticker)
        price = int(info["price"])
        db.execute("INSERT INTO transactions (id, ticker, shares, time, type, pricePerShare) VALUES (?, ?, ?, ?, 'SELL', ?)", user, ticker, shares, datetime.now(), price)
        totalprice = shares * price
        cash = db.execute("SELECT cash FROM users WHERE id = ?" , user)
        cash = cash[0]['cash']
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash + totalprice, user)
        return render_template("sold.html")
    return apology("TODO")

@app.route("/money", methods = ["GET", "POST"])
@login_required
def money():
    if (request.method == "GET"):
        return render_template("getmoney.html")
    if (request.method == "POST"):
        user = session.get("user_id")
        cash = db.execute("SELECT cash FROM users WHERE id = ?" , user)
        cash = cash[0]['cash']
        dollars = int(request.form.get("dollars"))
        if dollars < 0:
            return apology("enter positive dollar amnt", 500 )
        cash = cash + dollars
        db.execute("UPDATE users SET cash = ?", cash)
        return render_template("gotmoney.html")
    return apology("soemthing wrong ")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
