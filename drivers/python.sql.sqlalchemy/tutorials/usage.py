import os
import sys

if os.name == 'nt':
    if sys.version_info >= (3,6,0):
        sys.path.append(os.getcwd())
    if sys.version_info >= (3,8,0):
        os.add_dll_directory(os.getcwd())

from sqlalchemy import create_engine, Column, Integer, String, Date, Numeric, MetaData, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship, backref, joinedload
from sqlalchemy.orm.session import close_all_sessions

Base = declarative_base()

class User(Base):
    __tablename__ = 'users'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String(50))
    def __repr__(self):
        return "<User(id='%s', name='%s')>" % (self.id, self.name)

class Address(Base):
    __tablename__ = 'addresses'
    id = Column(Integer, primary_key=True, autoincrement=True)
    email = Column(String(50))
    user_id = Column(Integer, ForeignKey('users.id'))
    user = relationship("User", backref=backref('addresses'))
    def __repr__(self):
        return "<Address(email='%s')>" % self.email

try:
    engine = create_engine('ctsql://ADMIN:ADMIN@127.0.0.1/ctreeSQL', echo=False)
    Base.metadata.create_all(engine)
except Exception as e:
    print("error", e)
    if e.args[0].find('-20212') > -1:
        print("Perhaps your c-tree server is not running?")
        print("*** Execution aborted *** \nPress <ENTER> key to exit...")
        exit(1);

session = sessionmaker(bind=engine)()

u1 = User(name='u1')
u1.addresses=[Address(email='one'),Address(email='two')]

session.add(u1)
session.commit()

user_by_email = (session.query(User)
    .filter(Address.email=='one')
    #.options(joinedload(User.addresses))\
    .first())
print (user_by_email)

# This will cause an additional query by lazy loading from the DB unless you use joinedload.
print (user_by_email.addresses)

close_all_sessions()
import time
time.sleep(0.2)
Base.metadata.drop_all(engine)

