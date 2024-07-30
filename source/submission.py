from setting import Base
from sqlalchemy import Column, Integer, String


class Submission(Base):
    __tablename__ = 'submissions'
    id = Column(Integer, primary_key=True, index=True)
    problem_id = Column(String(63))
    contest_id = Column(String(63))
    language = Column(String(63))
    result = Column(String(15))
