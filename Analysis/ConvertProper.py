import pandas as pd
df = pd.read_csv('C:/Users/Arka-LAPPY/Desktop/TrafficCV/Analysis/test.csv')
sorted_df = df.sort_values(by=['Frame Number'], ascending=True)
sorted_df.to_csv('sorted.csv', index=False)