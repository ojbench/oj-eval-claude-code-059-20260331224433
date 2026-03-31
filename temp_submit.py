import requests
import json
import os

token = os.environ.get('ACMOJ_TOKEN')
api_base = "https://acm.sjtu.edu.cn/OnlineJudge/api/v1"

with open('src.hpp', 'r') as f:
    code_text = f.read()

headers = {
    "Authorization": f"Bearer {token}",
    "Content-Type": "application/x-www-form-urlencoded",
    "User-Agent": "ACMOJ-Python-Client/2.2"
}

data = {
    "language": "cpp",
    "code": code_text
}

response = requests.post(f"{api_base}/problem/1440/submit", headers=headers, data=data, timeout=30)
print(json.dumps(response.json(), indent=2))
