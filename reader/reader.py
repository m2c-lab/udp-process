# read parquet file
import pandas as pd
# import pyarrow.parquet as pq
# import pyarrow as pa
import os
import sys
import time
import datetime
import numpy as np


def read_parquet_file(file_path):
    """
    read parquet file
    :param file_path: parquet file path
    :return: pandas dataframe
    """
    df = pd.read_parquet(file_path)
    return df

# print the data table
def print_table(df):
    """
    print the data table
    :param df: pandas dataframe
    :return: None
    """
    print(df)

# main
if __name__ == '__main__':
    # start time
    start_time = time.time()

    # read parquet file
    file_path = 'test1.parquet'
    df = read_parquet_file(file_path)

    # print the data table
    print_table(df)

    # end time
    end_time = time.time()
    print('Time elapsed: ', end_time - start_time, ' seconds')
