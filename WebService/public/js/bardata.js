$(function(){
  var sizeChart = Morris.Bar({
          element: 'size-bar-chart',
          data: [{
              y: '2006',
              a: 100,
              b: 90
          }, {
              y: '2007',
              a: 75,
              b: 65
          }, {
              y: '2008',
              a: 50,
              b: 40
          }, {
              y: '2009',
              a: 75,
              b: 65
          }, {
              y: '2010',
              a: 50,
              b: 40
          }, {
              y: '2011',
              a: 75,
              b: 65
          }, {
              y: '2012',
              a: 100,
              b: 90
          }],
          xkey: 'y',
          ykeys: ['a', 'b'],
          labels: ['Series A', 'Series B'],
          hideHover: 'auto',
          resize: true
      });
    var portChart = Morris.Bar({
              element: 'port-bar-chart',
              data: [{
                  y: '2006',
                  a: 100,
                  b: 90
              }, {
                  y: '2007',
                  a: 75,
                  b: 65
              }, {
                  y: '2008',
                  a: 50,
                  b: 40
              }, {
                  y: '2009',
                  a: 75,
                  b: 65
              }, {
                  y: '2010',
                  a: 50,
                  b: 40
              }, {
                  y: '2011',
                  a: 75,
                  b: 65
              }, {
                  y: '2012',
                  a: 100,
                  b: 90
              }],
              xkey: 'y',
              ykeys: ['a', 'b'],
              labels: ['Series A', 'Series B'],
              hideHover: 'auto',
              resize: true
          });

          function portChartData(newData){
              portChart.setData(newData);
              portChart.redraw();
          };
          function sizeChartData(newData){
              sizeChart.setData(newData);
              sizeChart.redraw();
          }
          function portData(){
            $.ajax({
                url:"/getBardata.php",
                type: "get",
                dataType: "json",
                success:function(response){
                  portChartData(response);
                }
            });
          }
          function sizeData(){
            $.ajax({
                url:"/getSizedata.php",
                type:"get",
                dataType:"json",
                success:function(response){
                  sizeChartData(response);
                }
            });
          }

        setInterval(function updateChart(){
            portData();
            sizeData();
            //test($.parseJSON('[{"y":"2015", "a":10, "b":10}, {"y":"2016", "a":10, "b":10}, {"y":"2017", "a":10, "b":10}]'));
        },1000);
});
