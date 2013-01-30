<?php
require_once("shopaccess.php"); //get database credentials
require_once("header.php");
$query="select * from products";
$result=mysql_query($query);
$rows=mysql_num_rows($result);
echo "<table style=\"max-height:500px\">
  <tr><th>Name</th> <th>Price</th> <th>Item</></tr>";
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
