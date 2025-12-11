# C++ Bank Transactions Project
A simple c++ project simulating Transactions between Accounts owned by various Users. Users own and can open Accounts. You can either make a deposit on an Account you own, or make a Transaction between two Accounts.

It uses .csv files to store the data of Users, each with their own Accounts (alongside their own balance) and an history of the Transactions that took place.

## CSV Files Storage  
Depending on how you run this program the csv files will be created in different directories.

If you just run the compiled program (so the .exe file in windows for example), it'll look for csv files in the same directory,
and if there aren't it'll populate the folder with the needed .csv files. For example, when I ran it in VSCode, the csv files that are used when the program is ran without debugging were in the build folder.

If you run it from an ide in debug mode the files will be created at a different location (in my case in the same plase as the .cpp and .h project files
when using vscode).

The tests are built in such a way that they don't store or use existing csv files. They are built when the tests are run and deleted at the end of the tests. Also they use different names for the files, to avoid accidentally deleting the ones used in the main program.  