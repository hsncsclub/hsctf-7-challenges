<!doctype html>
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <title>Traffic Light W</title>
  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css" integrity="sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk" crossorigin="anonymous">
  <link href="dashboard.css" rel="stylesheet">
</head>

<body>
  <nav class="navbar navbar-dark sticky-top bg-dark flex-md-nowrap p-0">
    <a class="navbar-brand col-md-3 col-lg-2 mr-0 px-3" href="#">Shady Traffic Light Company</a>
  </nav>

  <div class="container">
    <div class="row">
      <main role="main">
        <div
          class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pt-3 pb-2 mb-3 border-bottom">
          <h1 class="h2">Traffic Light Dashboard</h1>
        </div>

        <canvas class="my-4 w-100" id="myChart" width="900" height="380"></canvas>

        <h2>Current Status</h2>
        <div class="table-responsive">
          <table class="table table-striped text-center">
            <thead>
              <tr>
                <th>#</th>
                <th>Active</th>
                <th>Hostname</th>
                <th>Port</th>
                <th>Firmware</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>1,001</td>
                <td>True</td>
                <td>traffic-light-1001</td>
                <td>80</td>
                <td><a href="firmware_upload.php?light=1001"><button type="button" class="btn btn-primary btn-sm">Upload Firmware</button></a></td>
              </tr>
              <tr>
                <td>1,002</td>
                <td>False</td>
                <td>Offline</td>
                <td>Offline</td>
                <td><button type="button" class="btn btn-primary btn-sm">Upload Firmware</button></td>
              </tr>
              <tr>
                <td>1,003</td>
                <td>False</td>
                <td>Offline</td>
                <td>Offline</td>
                <td><button type="button" class="btn btn-primary btn-sm">Upload Firmware</button></td>
              </tr>
              <tr>
                <td>1,004</td>
                <td>True</td>
                <td>traffic-light-1004</td>
                <td>80</td>
                <td><a href="firmware_upload.php?light=1004"><button type="button" class="btn btn-primary btn-sm">Upload Firmware</button></a></td>
              </tr>
              <tr>
                <td>1,005</td>
                <td>False</td>
                <td>Offline</td>
                <td>Offline</td>
                <td><button type="button" class="btn btn-primary btn-sm">Upload Firmware</button></td>
              </tr>
            </tbody>
          </table>
        </div>
      </main>
    </div>
  </div>
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/feather-icons/4.9.0/feather.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>
  <script src="dashboard.js"></script>
</body>

</html>
