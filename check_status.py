import requests
import json
import os

token = os.environ.get('ACMOJ_TOKEN')
api_base = "https://acm.sjtu.edu.cn/OnlineJudge/api/v1"

headers = {
    "Authorization": f"Bearer {token}",
    "User-Agent": "ACMOJ-Python-Client/2.2"
}

response = requests.get(f"{api_base}/submission/766493", headers=headers, timeout=10)
print(json.dumps(response.json(), indent=2))
