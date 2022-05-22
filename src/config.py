import json


class Config:
    def __init__(self, file_path: str) -> None:
        self.__file_path = file_path
        self.conf = self.load_config()

    def read_json(self):
        with open(self.__file_path, 'r', encoding='utf8') as f:
            return json.load(f)

    def write_json(self, data):
        with open(self.__file_path, 'w', encoding='utf8') as f:
            json.dump(data, f, indent=4)

    def load_config(self):
        conf = self.read_json()
        return conf

    def get_config(self):
        return self.conf

    def get_username(self) -> str:
        return self.get_config()['user']

    def update_config(self, submissions):
        last_submission_second = self.conf['from_second']
        for submission in submissions:
            if last_submission_second < submission['epoch_second'] + 1:
                last_submission_second = submission['epoch_second'] + 1
        self.conf['from_second'] = last_submission_second
        self.write_json(self.conf)
