# BasicBank

Transaction Class: Holds the amount and transaction date. < and > operator are overloaded to compare the dates of transaction. Transactions can be summed with other transactions or amounts. Also transactions can be streamed to show the amount and the date.

Account Class: Holds the user id, 2d Transaction array and an activity frequency per month. (This bank can only simulate a year for now, so the activity freguency is an integer array of size 12 such that element [0] is for January and so on.) Accounts can be summed and compared according to their ids. With balance() function total balance or balance between certain dates can be found. Accounts can also be streamed.

Bank Class: Hold the bank name, number of users and their Accounts. Can be summed with other Banks or accounts. (Existing accounts emerge.) [] operator is overloaded to reach the account using id. Finally, Bank can be streamed showing the accounts, balance of the bank and numbers of accounts that are eligible for a loan. (An account is eligible for a loan if the balance of two consecutive amounts are not negative.)
