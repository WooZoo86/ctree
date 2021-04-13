"""
Setup for SQLAlchemy dialect for c-tree SQL
"""
from setuptools import find_packages, setup
import os

setup_params = dict(
    name="sqlalchemy_ctsql",
    version='0.0.2',
    description="SQLAlchemy dialect for c-tree SQL",
    url="http://www.faircom.com",
    long_description="This is the c-tree SQL dialect driver for SQLAlchemy. It has support for Python 2.7, 3.3+. It supports SQLalchemy 1.0+",
    keywords='ctsql SQLAlchemy',
    packages=find_packages(),
    include_package_data=True,
    setup_requires=['pytest-runner'],
    tests_require=['pytest', 'mock'],
    test_suite="test.test_suite",
    zip_safe=False,
    entry_points={
        "sqlalchemy.dialects": [
            "ctsql = sqlalchemy_ctsql.dialect:ctsqlDialect",
        ]
    },
    install_requires=['pyctree', 'sqlalchemy'],
)

if __name__ == '__main__':
    setup(**setup_params)