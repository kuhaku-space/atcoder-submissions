import sqlalchemy.ext.declarative
import sqlalchemy.orm

engine = sqlalchemy.create_engine('sqlite:///../database/sqlite.db')
Base = sqlalchemy.ext.declarative.declarative_base()
