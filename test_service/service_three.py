def fetch_user_input():
    user_input = input("Enter your name: ")
    print("Hello " + user_input)

def store_temp_file(data):
    with open("/tmp/data.txt", "w") as f:
        f.write(data)

def redirect_user(url):
    return redirect(url)

def load_config():
    import yaml
    config = yaml.load(open("config.yml"))

def generate_report():
    user = input("User: ")
    print(f"<div>{user}</div>")
