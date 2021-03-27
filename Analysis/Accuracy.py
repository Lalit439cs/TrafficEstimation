import pandas as pd
df1 = pd.read_csv('C:/Users/Arka-LAPPY/Desktop/TrafficCV/Analysis/sorted.csv')
df2 = pd.read_csv('C:/Users/Arka-LAPPY/Desktop/TrafficCV/Analysis/compare.csv')
moving1=df1['Moving Density']
moving2=df2['Moving Density']
squaresum=0
for i in range (moving1.size):
        squaresum+=((moving2[i]-moving1[i])**2)
squaremean=squaresum/moving1.size
rootmeansquare=squaremean**0.5
print(rootmeansquare)