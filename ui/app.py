from flask import Flask, render_template, request, jsonify
from pathlib import Path
import subprocess

app = Flask(__name__)

source_path = Path(__file__).resolve()
source_dir = source_path.parent
root_dir = source_dir.parent

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/run_self_test', methods=['POST'])
def run_self_test():
    self_test_cmd = root_dir / "scripts" / "self_test.sh"
    try:
        result = subprocess.check_output(str(self_test_cmd), shell=True, text=True)
        return jsonify({'result': result, 'success': True})
    except subprocess.CalledProcessError as e:
        return jsonify({'result': f"Error: {e}", 'success': False})

@app.route('/receive_udp', methods=['POST'])
def receive_udp():
    local_ip = request.form.get('localIP')
    local_port = request.form.get('localPort')
    remote_ip = request.form.get('remoteIP')
    remote_port = request.form.get('remotePort')
    timeout = request.form.get('timeout')

    # First save config to file

    # Run C++ program to receive UDP data

    # Return result (change this to something more useful)
    result = "Received UDP data. Local IP: {}, Local Port: {}, Remote IP: {}, Remote Port: {}, Timeout: {}".format(
        local_ip, local_port, remote_ip, remote_port, timeout)

    return jsonify({'result': result})

if __name__ == '__main__':
    app.run(debug=True)
