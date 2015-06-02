(function ($) {


  $(document).ready(function(){
    $("#edit-choice-0").click(function(){
      $('input[name="Knowledge"]').val('');
      $('input[name="Attitude"]').val('');
      $('input[name="Friendliness"]').val('');
      $("span").removeClass("redstar");
    });
    $("#edit-choice-1").click(function(){
      $('input[name="Knowledge"]').val('');
      $('input[name="Attitude"]').val('');
      $('input[name="Friendliness"]').val('');
      $("span").removeClass("redstar");
    });
    $("span.knowledge").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.knowledge").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.knowledge."+i).addClass("redstar");
      }
      $('input[name="Knowledge"]').val(no);
    });
    $("span.attitude").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.attitude").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.attitude."+i).addClass("redstar");
      }
      $('input[name="Attitude"]').val(no);
    });
    $("span.friendliness").click(function(){
      $len = $(this).attr("class");
      $s = $len.split(" ");
      var no = $s[3];
      $("span.friendliness").removeClass("redstar");
      for(var i = 1 ; i <= no ;i++) {
        $("span.whitestar.spanspace.friendliness."+i).addClass("redstar");
      }
      $('input[name="Friendliness"]').val(no);
    });
  });
  Drupal.behaviors.feedback = {
    attach: function (context, settings) {
      console.log(Drupal.ajax);
      $("span").removeClass("redstar");
      var kn = $('input[name="Knowledge"]').val();
      var at = $('input[name="Attitude"]').val();
      var fn = $('input[name="Friendliness"]').val();
      for(var i = 1 ; i <= kn ;i++) {
        $("span.whitestar.spanspace.knowledge."+i).addClass("redstar");
      }
      for(var i = 1 ; i <= at ;i++) {
        $("span.whitestar.spanspace.attitude."+i).addClass("redstar");
      }
      for(var i = 1 ; i <= fn ;i++) {
        $("span.whitestar.spanspace.friendliness."+i).addClass("redstar");
      }
    }
  };

}(jQuery));
