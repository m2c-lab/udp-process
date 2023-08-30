# read parquet file
import pandas as pd
# import pyarrow.parquet as pq
# import pyarrow as pa
import os
import sys
import time
import datetime
import numpy as np
# plot
import matplotlib.pyplot as plt

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
    # print_table(df)

    timestamp = df.iloc[0, 0]
    noise = df.iloc[0, 1]
    
    # print timestamp and noise in HEX
    print('timestamp: ', hex(timestamp))
    print('noise: ', hex(noise))


    # get the CIR of a row
    CIR = df.iloc[2, 2:258]

    # Get I and Q data, from column CIR0 to CIR255.
    # Each data is 32 bits, and I has the higher 16 bits, Q has the lower 16 bits, interpret as 16-bit signed integer.
    CIR_I = []
    CIR_Q = []
    for i in range(0, 256):
        # Extract the 16-bit signed integer I and Q components from the 32-bit value
        Q_component = np.int16(CIR[i] & 0xffff)  # Mask the lower 16 bits
        I_component = np.int16(CIR[i] >> 16)     # Shift and mask the higher 16 bits

        CIR_I.append(I_component)
        CIR_Q.append(Q_component)

    # plot
    plt.figure(figsize=(10, 5))
    plt.plot(CIR_I, label='I')
    plt.plot(CIR_Q, label='Q')
    plt.legend()
    plt.show()


    # end time
    end_time = time.time()
    print('Time elapsed: ', end_time - start_time, ' seconds')
