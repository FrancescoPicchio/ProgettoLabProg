# C++ Bank Transactions Project
A simple c++ project simulating Transactions between Accounts owned by various Users. Users own and can open Accounts. You can either make a deposit on an Account you own, or make a Transaction between two Accounts.

It uses .csv files to store the data of Users, each with their own Accounts (alongside their own balance) and an history of the Transactions that took place.

## ATTENTION:  
Depending on how you run this program csv files will be created in different directories.

If you just run the compiled program (so the .exe file in windows for example), it'll look for csv files in the same directory,
and if there aren't it'll populate the folder with the needed .csv files.

If you run it from an ide in debug mode the files will be created at a different location (in my case in the same plase as the .cpp and .h project files
when using vscode).