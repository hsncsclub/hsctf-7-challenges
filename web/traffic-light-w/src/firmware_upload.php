<!doctype html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <title>Firmware Upload</title>
  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">
  <link href="dashboard.css" rel="stylesheet">
</head>

<body>
  <nav class="navbar navbar-dark sticky-top bg-dark flex-md-nowrap p-0">
    <a class="navbar-brand col-md-3 col-lg-2 mr-0 px-3" href="/">Shady Traffic Light Company</a>
  </nav>

  <div class="container">
    <div class="h-100 d-flex justify-content-center align-items-center border-bottom">
      <div>
        <br><br><br>
<?php
if(isset($_GET["light"])) {
  $light = $_GET["light"];
  if ($light === "1001") {
    echo "<h1 class='h2'>{$light}</h1>";
    echo '<form action="/firmware_upload.php" method="GET"> <div class="form-group"> <label for="xml">Upload your XML firmware.<br>Example: <a href="example"><code>example</code></a></label> <textarea class="form-control" id="xml" name="xml" rows="8"></textarea><br><button type="submit" class="btn btn-primary btn-block">Submit</button></div> </form>';
  }
  else if ($light === "1004") {
    echo "<h1 class='h2'>{$light}</h1>";
    echo "<h1 class=\"h2\">Error: High CPU Usage</h1>";
  }
  else {
    echo "<h1 class=\"h2\">Error: Not active</h1>";
  }
}
?>

<?php
if (isset($_GET["xml"])) {
  libxml_disable_entity_loader (false);

  $xml = strlen($_GET["xml"]) > 0 ? $_GET["xml"] : "Firmware Update Failed";

  $document = new DOMDocument();
  $document->loadXML($xml, LIBXML_NOENT | LIBXML_DTDLOAD);
  $parsed = simplexml_import_dom($document);

  echo $parsed->content;
}
?>

</div>
    </div>
  </div>
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>
</body>

</html>
