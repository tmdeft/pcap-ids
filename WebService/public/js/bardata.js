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
      Morris.Bar({
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

          function test(newData){
              sizeChart.setData(newData);
              sizeChart.redraw();
          };
          function jsonData(){
            $.ajax({
                url:"/getBardata.php",
                type: "get",
                dataType: "json",
                success:function(response){
                  test(response)
                }
            });
          }

        setInterval(function updateChart(){
            jsonData();
            //test($.parseJSON('[{"y":"2015", "a":10, "b":10}, {"y":"2016", "a":10, "b":10}, {"y":"2017", "a":10, "b":10}]'));
        },1000);
});
