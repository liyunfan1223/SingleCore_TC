import os
import MySQLdb # import t/he MySQLdb module
# from dotenv import load_dotenv
# load_dotenv()

# Create the connection object
connection = MySQLdb.connect(
    host="124.223.191.243",
    user="root",
    passwd="root",
    db="characters",
)

# Create cursor and use it to execute SQL command
cursor = connection.cursor()
# cursor.execute("select @@version")
# version = cursor.fetchone()

cursor.execute("select * from item_instance")
count = cursor.fetchone()
idx = 0
mp = {}
while count:
    guid = count[0]
    # if guid < 1000:
    #     count = cursor.fetchone()
    #     continue
    if guid not in mp.keys():
        mp[guid] = idx
    idx += 1
    if (idx % 10000 == 0):
        print(guid, idx)
    count = cursor.fetchone()

cursor.close()
print("!", len(mp), idx)
cursor = connection.cursor()

ok = 0
for key in mp.keys():
    value = mp[key]
    print("!", key, value)
    cursor.execute(f"update item_soulbound_trade_data set itemGuid={value} where itemGuid={key};")
    cursor.execute(f"update character_inventory set item={value} where item={key};")
    cursor.execute(f"update character_inventory set bag={value} where bag={key};")
    cursor.execute(f"update item_instance set guid={value} where guid={key};")
    # ok += 1
    # if (ok % 2000 == 0):
    #     print("?!?!", ok)
    #     cursor.close()
    #     break
    # cursor.close()

connection.commit()
connection.close()