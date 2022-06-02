"""
atcoder-submissions
https://github.com/kuhaku-space/atcoder-submissions
Copyright (c) 2022 Yuya Terashima
Released under the MIT license
https://github.com/kuhaku-space/atcoder-submissions/blob/main/LICENSE

Includes kuriyan1204/AtCoder-AutoClone
https://github.com/kuriyan1204/AtCoder-AutoClone
Copyright (c) 2022 Hiroto Kurita
Released under the MIT license
https://github.com/kuriyan1204/AtCoder-AutoClone/blob/main/LICENSE
"""

from api import API
from database import Database
from config import Config

CONFIG_PATH = '../config/config.json'
DATABASE_NAME = '../database/submission.db'
SUBMISSION_TABLE_NAME = 'atcoder'
CODE_TABLE_NAME = 'code'
API_URL = 'https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions?'
COLUMN_TYPE = {'id': 'integer primary key', 'problem_id': 'text',
               'contest_id': 'text', 'result': 'text', }


def main():
    database = Database(DATABASE_NAME)
    database.create_table(SUBMISSION_TABLE_NAME, COLUMN_TYPE)
    database.create_table(CODE_TABLE_NAME, COLUMN_TYPE)

    api = API(API_URL)
    conf = Config(CONFIG_PATH)
    submissions = api.get_submissions(conf)
    database.update_database(SUBMISSION_TABLE_NAME, COLUMN_TYPE, submissions)
    database.save_code(SUBMISSION_TABLE_NAME,
                       CODE_TABLE_NAME, COLUMN_TYPE, submissions)

    database.close_database()


if __name__ == '__main__':
    main()
