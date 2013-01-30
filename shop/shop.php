<?php
require_once("header.php");
require_once("shopaccess.php"); //get database credentials
$db_server = mysql_connect($db_hostname, $db_user, $db_password);
mysql_select_db($db_database);
$query="select * from products";
$result=mysql_query($query);
$rows=mysql_num_rows($result);
//loop through db to display products with name, image and price
for($i=0; $i<$rows; $i++)
{
  $row=mysql_fetch_row($result);
  echo "<tr>";
  for($h=0; $h<2; $h++) echo "<td>$row[$h]</td>";
  echo "<td><img src=\"$row[2]\" height=\"100\" width=\"100\" align=\"center\" /></td>";
  echo "</tr>";
}

?>
        </table>
      </div>
<?php include("footer.php"); ?>
