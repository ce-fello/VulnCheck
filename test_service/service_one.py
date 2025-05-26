import os
import subprocess
import sqlite3
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route("/login")
def login():
    username = request.args.get("user")
    password = request.args.get("pass")
    query = "SELECT * FROM users WHERE user = \"" + username + "\" AND pass = \"" + password + "\""
    db = sqlite3.connect("users.db")
    db.execute(query)
    return "OK"

@app.route("/search")
def search():
    user_input = request.args.get("q")
    return f"<div>{user_input}</div>"

@app.route("/open")
def open_file():
    user_input = request.args.get("file")
    with open(user_input, "r") as f:
        return f.read()

@app.route("/exec")
def exec_code():
    code = request.args.get("code")
    exec(code)
    return "Executed"

@app.route("/subproc")
def subproc():
    user_input = request.args.get("cmd")
    subprocess.Popen(user_input, shell=True)
    return "Running"

if __name__ == "__main__":
    app.run()
