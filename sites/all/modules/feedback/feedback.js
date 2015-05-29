(function ($) {

  $(document).ready(function(){
    $("#edit-choice-0").click(function(){
      $("input:text").val('');
    });
  });

  $(document).ready(function(){
    $("span.knowledge").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
     // $("span").eq(i).addClass("redstar");
      var i;
      // for(i=1 ; i=<no ;i++) {
      //   $("span")."whitestar.spanspace.knowledge".i.addClass("redstar");

      // }
      if($(this).attr("class") == "whitestar spanspace knowledge 4")
      {
        alert("hello");
      }

    });
  });

$(document).ready(function(){
    $("whitspace").click(function(){
      if($(this).attr("class").match("abc") && $(this).attr("class").match("xyz") )
      {
        alert("hello");
      }


  $(document).ready(function(){
    $("span.attitude").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      alert($s[3]);

    });
  });
  $(document).ready(function(){
    $("span.friendliness").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      alert($s[3]);

    });
  });

  Drupal.behaviors.feedback = {
    attach: function (context, settings) {
      // Your Javascript code goes here
    // alert(Drupal.settings.feedback.tax_rate);

    }
  };
}(jQuery));
