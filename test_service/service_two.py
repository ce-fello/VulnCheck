def generate_promocode_error(error, promocode):
    if error == 'invalid_code':
        return ('<p>Sorry, {{username}}, your promocode - "%s" is invalid.</p>' % promocode)
    elif error == 'code_is_used': 
        return ('<p>Sorry, promocode "%s" is already used</p>' % promocode)
    else:
        return '<p>Unknown error with promocode</p>'
    
def apply_promocode(db, code, basket_price):      
    promocode = db.execute("SELECT id, code, status, amount FROM Promocode WHERE code = " + code + "").fetchone()
    if not promocode:
        return (basket_price, generate_promocode_error('invalid_code', code))
    elif promocode['status'] == 'active':
        basket_price -= promocode['amount']
        db.execute("UPDATE Promocode SET status = 'used' WHERE id = %d" % promocode['id'])
        return (basket_price, None)
    elif promocode['status'] == 'used':
        return (basket_price, generate_promocode_error('code_is_used', code))

@app.route("/add_product", methods=("POST"))
def add_product():
    db = get_db()
    basket_id = int(request.form["basket_id"])
    product_id = int(request.form["product_id"])
    count = int(request.form["product_count"])
    return_url = request.args.get("return_url")
    product = db.execute("SELECT id, price FROM Product WHERE id=%d" % product_id).fetchone()
    db.execute("UPDATE Basket SET price = price + %d WHERE id = %d" %(count*product['price'], basket_id))
    db.execute("INSERT INTO BasketProducts (basket_id, product_id, count) VALUES (%d, %d, %d)" % (basket_id, product_id, count))
    db.commit()
    return redirect(return_url, code=302)

@app.route("/pay", methods=("POST"))
def pay():
    error = ''
    db = get_db()
    basket_id = int(request.form["basket_id"])
    wallet_id = int(request.form["wallet_id"])
    promocode = request.form["promocode"]
    return_url = request.args.get("return_url")
    basket = db.execute("SELECT id, price FROM Basket WHERE id = %d" % basket_id).fetchone()
    wallet = db.execute("SELECT id, amount FROM Wallet WHERE id = %d" % wallet_id).fetchone()
    if promocode:
        (basket['price'], promocode_error) = apply_promocode(db, promocode, basket['price'])
        error += promocode_error
    if wallet['amount'] >= basket['price']:
        db.execute("UPDATE Basket SET status = 'paid' WHERE id = %d" % basket['id'])
        new_amount = wallet['amount'] - basket['price']
        db.execute("UPDATE Wallet SET amount = amount - %d WHERE id = %d" % (new_amount, wallet['id']))
        db.commit()
    return render_template_string('''
        {% extends 'base.html' %}
        {% block error %}
        ''' + error + '''
        {% endblock %}
        
        {% block content %}
            Hi, {{username}}. Your basket successfully paid!
            <a href="{{ return_url }}">back to previous page</a>
        {% endblock %}
        ''', username=g['username'], return_url=return_url)
