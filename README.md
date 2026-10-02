\# Simple Bank System Using Functional Programming (C++)



console-based banking management system developed in C++ featuring multi-user role-based access control (RBAC), file handling, transaction processing, and user management modules.



\---



\## Features



\### 1. Authentication \& Security

\- \*\*Secure Login System:\*\* Validates usernames and passwords against persistent storage (`Users.txt`).

\- \*\*Role-Based Access Control (RBAC):\*\* Granular permission management system allowing administrators to restrict access to specific system menus and operations.

\- \*\*Full Access / Custom Permissions:\*\* Supports absolute permissions (`-1`) or customized bitwise permission flags.



\### 2. Client Management

\- \*\*View Client List:\*\* Displays a formatted table of all active clients with their account details and balances.

\- \*\*Add New Clients:\*\* Supports single or batch creation with automatic validation to prevent duplicate account numbers.

\- \*\*Find Client:\*\* Rapid search functionality by account number.

\- \*\*Update Client Information:\*\* Modify PIN codes, names, phone numbers, and balances.

\- \*\*Delete Client:\*\* Safe soft-deletion mechanism with permanent file updating.



\### 3. Transactions Menu

\- \*\*Deposit:\*\* Add funds securely to any valid client account.

\- \*\*Withdraw:\*\* Process withdrawals with built-in validation preventing amounts from exceeding available balances.

\- \*\*Total Balances:\*\* View a comprehensive report of all client balances alongside the total aggregate sum in the bank.



\### 4. User Management

\- \*\*List Users:\*\* View all registered system operators and their permission levels.

\- \*\*Add New Users:\*\* Create operators and assign granular menu permissions.

\- \*\*Update Users:\*\* Modify operator credentials and access rights.

\- \*\*Delete Users:\*\* Remove operators (with built-in protection preventing the deletion of the primary `Admin` account).

\- \*\*Find User:\*\* Search operators by username.



\---



\## File Structure \& Storage

The application utilizes flat-file text storage with custom delimiter separation (`#//#`):

\- `Clients.txt`: Stores client records (`AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance`).

\- `Users.txt`: Stores user credentials and access permissions (`UserName#//#Password#//#Permissions`).



\---



\## Code Architecture \& Enumerations



\### Enums

\- `enMainMenueOptions`: Controls primary dashboard navigation (List Clients, Add Client, Delete Client, Update Client, Find Client, Transactions, Manage Users, Logout).

\- `enTransactionsMenueOptions`: Manages financial operations (Deposit, Withdraw, Total Balances, Return to Main Menu).

\- `enManageUsersMenueOptions`: Manages administrative operations (List Users, Add User, Delete User, Update User, Find User, Return to Main Menu).

\- `enMainMenuePermissions`: Bitwise permission mapping flags for access validation.



\### Core Structures

\- `sClient`: Represents banking client attributes.

\- `stUser`: Represents system user credentials and authorization rights.

---

### Test Account

**Username:** `Admin`
**Password:** `1995`

---



\---



