import sqlite3
from submission import Submission


class Database:
    def __init__(self, database_name: str) -> None:
        self.connect_database(database_name)

    def connect_database(self, database_name: str) -> None:
        self.__con = sqlite3.connect(database_name)
        self.__cur = self.__con.cursor()

    def close_database(self) -> None:
        self.__con.commit()
        self.__con.close()

    def exists_table(self, table_name: str) -> bool:
        sql_str = (f"select count(*) from sqlite_master"
                   f"where type='table' and name='{table_name}'")
        self.__cur.execute(sql_str)
        return self.__cur.fetchone()[0] != 0

    def create_table(self, table_name: str, columns_type: dict[str, str]) -> None:
        sql_str = f'create table if not exists {table_name} ('
        for column in columns_type:
            sql_str += f'{column} {columns_type[column]}, '
        sql_str = sql_str[:-2]
        sql_str += ')'
        self.__cur.execute(sql_str)

    def delete_table(self, table_name: str) -> None:
        self.__cur.execute(f'drop table {table_name}')

    def exists_record(self, table_name: str, submission_data) -> bool:
        sql_str = f'select count(*) from {table_name} where id={submission_data["id"]}'
        self.__cur.execute(sql_str)
        return self.__cur.fetchone()[0] != 0

    def insert_record(self, table_name: str, columns_type: dict[str, str], submission_data) -> None:
        values_str = str(tuple(submission_data[i] for i in columns_type))
        values_str = values_str.replace('None', 'null')
        sql_str = f'insert into {table_name} {tuple(columns_type.keys())} values {values_str}'
        self.__cur.execute(sql_str)

    def update_database(self, table_name: str, columns_type: dict[str, str], submissions) -> None:
        for submission_data in submissions:
            if not self.exists_record(table_name, submission_data):
                self.insert_record(table_name, columns_type, submission_data)

    def is_latest_submission(self, table_name: str, submission_data) -> bool:
        sql_str = (f"select max(id) from '{table_name}'"
                   f"where problem_id='{submission_data['problem_id']}' and "
                   f"contest_id='{submission_data['contest_id']}' and result='AC'")
        self.__cur.execute(sql_str)
        return self.__cur.fetchone()[0] == submission_data['id']

    def is_saved_submission(self, table_name: str, submission_data) -> bool:
        sql_str = (f"select count(*) from '{table_name}'"
                   f"where id={submission_data['id']}")
        self.__cur.execute(sql_str)
        return self.__cur.fetchone()[0] != 0

    def save_code(self, search_table_name: str, save_table_name: str,
                  columns_type: dict[str, str], submissons) -> None:
        cnt = 0
        for submission_data in submissons:
            if (self.is_latest_submission(search_table_name, submission_data) and
                    not self.is_saved_submission(save_table_name, submission_data)):
                Submission.write_code(submission_data)
                self.insert_record(
                    save_table_name, columns_type, submission_data)
                cnt += 1
            if cnt >= 10:
                break
