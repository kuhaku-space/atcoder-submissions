import json


class Config:
    def __init__(self, file_path: str) -> None:
        self.__file_path = file_path
        self.conf = self.load_config()

    def read_json(self):
        with open(self.__file_path, "r", encoding="utf8") as f:
            return json.load(f)

    def load_config(self):
        conf = self.read_json()
        return conf

    def get_config(self):
        return self.conf

    def get_username(self) -> str:
        return self.get_config()["user"]
