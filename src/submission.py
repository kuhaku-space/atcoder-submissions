import os
import re
import time
from bs4 import BeautifulSoup
import requests

EXTENSIONS = {"C++": "cpp", "C#": "cs", "C": "c",
              "Python": "py", "PyPy": "py", "Ruby": "rb", "Text": "txt", }


class Submission:
    def __init__(self) -> None:
        pass

    @staticmethod
    def is_ac(submission_data) -> bool:
        return submission_data['result'] == 'AC'

    @staticmethod
    def get_contest_type(submission_data) -> str:
        contest_name = submission_data['contest_id']
        if re.fullmatch(r'abc\d{3}', contest_name) is not None:
            return 'abc'
        if re.fullmatch(r'arc\d{3}', contest_name) is not None:
            return 'arc'
        if re.fullmatch(r'agc\d{3}', contest_name) is not None:
            return 'agc'
        return 'other'

    @staticmethod
    def get_extension(submission_data) -> str:
        extension = None
        for lang, lang_extension in EXTENSIONS.items():
            if lang in submission_data['language']:
                extension = lang_extension
                break
        return extension

    @staticmethod
    def get_code(submission_data) -> str:
        submission_url = (f"https://atcoder.jp/contests/{submission_data['contest_id']}/"
                          f"submissions/{submission_data['id']}")
        time.sleep(2)
        response = requests.get(submission_url)
        if response.status_code != 200:
            return None
        return BeautifulSoup(response.content, 'html.parser').pre.string

    @staticmethod
    def write_code(submission_data) -> None:
        submission_code = Submission.get_code(submission_data)
        if submission_code is None:
            return
        extension = Submission.get_extension(submission_data)
        path = (f"../code/{Submission.get_contest_type(submission_data)}/"
                f"{submission_data['contest_id']}/{submission_data['problem_id']}.{extension}")
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding='utf8') as f:
            f.write(submission_code)
