from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/execute_command', methods=['POST'])
def execute_command():
    command = request.form.get('command')
    try:
        result = subprocess.check_output(command, shell=True, text=True)
        return jsonify({'result': result})
    except subprocess.CalledProcessError as e:
        return jsonify({'result': f"Error: {e}"})

if __name__ == '__main__':
    app.run(debug=True)
