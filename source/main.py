import json
import time

import requests
import sqlalchemy
import sqlalchemy.ext.declarative
import sqlalchemy.orm

from src.config import Config
from src.setting import Base, engine
from src.submission import Submission

API_URL = "https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions?"
CONFIG_PATH = "../config/config.json"

EXTENSIONS = {
    "C++": "cpp",
    "C#": "cs",
    "C": "c",
    "Python": "py",
    "PyPy": "py",
    "Ruby": "rb",
    "Text": "txt",
}


Base.metadata.create_all(engine)
Session = sqlalchemy.orm.sessionmaker(bind=engine)
session = Session()


def get_submissions(conf: Config):
    unix_time = 0
    while True:
        params = {"user": conf.get_username(), "from_second": unix_time}
        time.sleep(2)
        response = requests.get(API_URL, params=params)
        print(f"Request for {response.url}")
        submissions = json.loads(response.text)
        if not submissions:
            break
        for submission_data in submissions:
            unix_time = max(unix_time, submission_data["epoch_second"] + 1)
            submission = Submission(
                id=submission_data['id'],
                problem_id=submission_data['problem_id'],
                language=submission_data['language'],
                contest_id=submission_data['contest_id'],
                result=submission_data['result']
            )
            query_result = session.get(Submission, submission.id)
            if not query_result:
                session.add(submission)
    session.commit()


def main():
    conf = Config(CONFIG_PATH)
    get_submissions(conf)


if __name__ == "__main__":
    main()
