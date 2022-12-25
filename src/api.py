import json
import time

import requests

from config import Config


class API:
    def __init__(self, url: str) -> None:
        self.__url = url

    def get_submissions(self, conf: Config):
        all_submissions = []
        unix_time = 0
        while True:
            params = {"user": conf.get_username(), "from_second": unix_time}
            time.sleep(2)
            res = requests.get(self.__url, params=params)
            submissions = json.loads(res.text)
            if not submissions:
                break
            all_submissions += submissions
            for submission_data in submissions:
                unix_time = max(unix_time, submission_data["epoch_second"] + 1)
        return all_submissions
