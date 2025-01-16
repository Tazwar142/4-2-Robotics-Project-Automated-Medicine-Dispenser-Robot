from flask import Flask, jsonify
import pandas as pd

app = Flask(__name__)

# Path to the Excel file
EXCEL_FILE_PATH = "C:\\Users\\LENOVO\\Desktop\\Book1.xlsx"

@app.route('/get_data', methods=['GET'])
def get_data():
    # Read the Excel file
    df = pd.read_excel(EXCEL_FILE_PATH)
    # Convert the DataFrame to JSON
    data = df.to_dict(orient='records')
    return jsonify(data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000,debug=True)