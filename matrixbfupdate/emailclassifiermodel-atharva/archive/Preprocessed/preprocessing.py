import csv
import string

with open('spamemails.csv', 'r') as input_file, open('output.csv', 'w', newline='') as output_file:
    reader = csv.reader(input_file)
    writer = csv.writer(output_file)
    for row in reader:
        cleaned_row = []
        for item in row:
            # Remove all punctuation marks from the string
            cleaned_item = item.translate(str.maketrans('', '', string.punctuation))
            cleaned_row.append(cleaned_item)
        writer.writerow(cleaned_row)

# with open('output.csv', 'r') as input_file, open('keywords.csv', 'w', newline='') as output_file:
#     reader = csv.reader(input_file)
#     writer = csv.writer(output_file)
#     #removing acrticles, prepositions, verbs
#     data = ['a','to','of','we','are','an', 'the','in', 'on', 'at','be', 'have', 'do', 'say', 'get', 'make', 'go', 'take', 'see', 'come', 'know', 'give', 'find', 'think', 'tell', 'become', 'feel', 'leave', 'put', 'mean', 'keep', 'let', 'begin', 'seem', 'help', 'talk', 'turn', 'start', 'show', 'hear', 'play', 'run', 'move', 'like', 'live', 'believe', 'hold', 'bring', 'happen', 'write', 'provide', 'sit', 'stand', 'lose', 'pay', 'meet', 'include', 'continue', 'set', 'learn', 'change', 'lead', 'understand', 'watch', 'follow', 'stop', 'create', 'speak', 'read', 'allow', 'add', 'spend', 'grow', 'open', 'walk', 'win', 'offer', 'remember', 'love', 'consider', 'appear', 'buy', 'wait', 'serve', 'die', 'send', 'expect', 'build', 'stay', 'fall', 'cut', 'reach', 'kill', 'remain', 'suggest', 'raise', 'pass', 'sell', 'require', 'report', 'decide', 'pull', 'call', 'receive', 'agree', 'support', 'explain', 'check', 'develop', 'belong', 'cover', 'reach', 'increase', 'move', 'return', 'divide', 'apply', 'marry', 'prepare', 'beat', 'pick', 'raise', 'express', 'strike', 'win', 'wind', 'operate', 'touch', 'press', 'shoot', 'clean', 'contain', 'apply', 'travel', 'raise', 'describe', 'deliver', 'believe', 'hold', 'exchange', 'fly', 'spend', 'recover', 'lose', 'walk', 'push', 'decide', 'wait', 'wear', 'spread', 'overcome', 'advise', 'gather', 'enter', 'touch', 'create', 'rain', 'care', 'shoot', 'carry', 'win', 'dream', 'imagine', 'smile', 'introduce', 'preserve', 'drink', 'climb', 'sing', 'refer', 'finish', 'visit', 'form', 'prove', 'drive', 'rely', 'sleep', 'smell', 'survive']
#     for row in reader:
#         y=[]
#         for a in row:
#             a=a.split()
#             l=[]
#             for k in a:
#                 count = 0
#                 for z in data:
#                     if z==k:
#                         count = 1
#                 if count == 0:
#                     l.append(k)
#             l = [''.join(c for c in s)for s in l]
#             y.append(l)
#         y = [' '.join(c for c in s)for s in y]
#         writer.writerow(y)