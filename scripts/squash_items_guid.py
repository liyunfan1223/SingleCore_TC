import os
import MySQLdb # import t/he MySQLdb module
# from dotenv import load_dotenv
# load_dotenv()

# Create the connection object
connection = MySQLdb.connect(
    host="127.0.0.1",
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
print("Collecting item guids...")
while count:
    guid = count[0]
    if guid not in mp.keys():
        mp[guid] = idx
    count = cursor.fetchone()
    idx += 1

cursor.close()
print("Collected item guids number:", idx)
cursor = connection.cursor()

for key in mp.keys():
    value = mp[key]
    if (value % 1000 == 0):
        print(f"Turning old guid: {key} -> {value}")
    cursor.execute(f"update item_soulbound_trade_data set itemGuid={value} where itemGuid={key};")
    cursor.execute(f"update character_inventory set item={value} where item={key};")
    cursor.execute(f"update character_inventory set bag={value} where bag={key};")
    # res = cursor.rowcount
    # print(res)
    cursor.execute(f"update item_instance set guid={value} where guid={key};")

print("Item guid squash succeed.")
connection.commit()
connection.close()
