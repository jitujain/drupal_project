(function ($) {

  $(document).ready(function(){
    $("#edit-choice-0").click(function(){
      $("input:text").val('');
      $("span").removeClass("redstar");
    });
  });
  $(document).ready(function(){
    $("#edit-choice-1").click(function(){
      $("input:text").val('');
      $("span").removeClass("redstar");
    });
  });

  $(document).ready(function(){
    $("span.knowledge").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.knowledge").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.knowledge."+i).addClass("redstar");
      }
      $("#edit-knowledge").val(no);


    });
  });

  $(document).ready(function(){
    $("span.attitude").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.attitude").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.attitude."+i).addClass("redstar");
      }
      $("#edit-attitude").val(no);

    });
  });
  $(document).ready(function(){
    $("span.friendliness").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.friendliness").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.friendliness."+i).addClass("redstar");
      }
      $("#edit-friendliness").val(no);

    });
  });

  Drupal.behaviors.feedback = {
    attach: function (context, settings) {
      // Your Javascript code goes here
    // alert(Drupal.settings.feedback.tax_rate);

    }
  };
}(jQuery));
