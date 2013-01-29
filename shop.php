<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns = "http://www.w3.org/1999/xhtml">
  <head>
    <title>Welcome to our shop!</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
  </head>
  <body>
    <?php include("header.php"); ?>
    <?php include("nav.php"); ?>
    <br />
    <?php
    require_once("shopaccess.php"); //get database credentials
    $db_server = mysql_connect($db_hostname, $db_user, $db_password);
    mysql_select_db($db_database);
    ?>
    <?php
    $query="select * from products";
    $result=mysql_query($query);
    $rows=mysql_num_rows($result);
    echo "<div class = \"content\" >";
      include("logo.php");
      echo "<table style=\"max-height:500px\"><tr><th>Name</th> <th>Price</th> <th>Item</></tr>";
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
    </body>
  </html>
