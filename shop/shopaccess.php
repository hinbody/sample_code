<?php 
$db_database=''; // database name
$db_hostname=''; // db hostname
$db_user='';     // db username
$db_password=''; // db password for username
$db_server = mysql_connect($db_hostname, $db_user, $db_password);
mysql_select_db($db_database);
