Firebird ODBC Driver v2.2 Readme (SD Edition)
=============================================

o What's new
o Installation
o Configuration
o Known Issues
o Feedback


What's New
----------

Welcome to the latest release of the Firebird ODBC driver. This release
sees some advances in the driver. Notable changes are:

o Increased conformance to the different ODBC specifications.
o Improved installation (and uninstallation) routines for Win32.


o Installation
--------------

Just click through the binary executable for install.


o Configuration
---------------

Database connections are configured from the Database Administrator
applet in the Control Panel.


o Known Issues
--------------

Applications such as OpenOffice Quickstarter retain a lock on the driver 
libraries. Installation and Uninstallation will fail under these circumstances. 
The only work around is to ensure that all applications that might be
using the driver are closed before you start installation.

There are no other known issues at this time.


Feedback
--------

If you found an issue with this fork add it to 
https://github.com/aafemt/firebird-odbc-driver/issues
preferable with testcase and/or ODBC trace file
demonstrating what's wrong.
