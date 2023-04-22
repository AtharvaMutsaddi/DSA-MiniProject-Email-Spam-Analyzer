import pandas as pd

# df=pd.read_csv('spam_ham_dataset.csv')
# spamdf=df[df.label_num == 1]
# # print(spamdf.shape)
# spamdf=spamdf.head(719)

# # opening the file in read mode
# my_file = open("spamemailIDs.txt", "r")
# # reading the file
# data = my_file.read()
# data_into_list = data.split("\n")
# spamdf=spamdf.drop(['label','label_num'], axis='columns')
# spamdf['senderaddress']=data_into_list
# spamdf.to_csv('spamemails.csv')
# print(spamdf)

df=pd.read_csv('testemailIDs.csv')
testdf=df['label'].fillna(int(1))
testdf.to_csv('finaltestemailIDs.csv')

