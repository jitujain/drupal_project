(function ($) {

  $(document).ready(function(){
    //On select Add button remove the redstar class.
    $("#edit-choice-0").click(function(){
      $('input[name="Knowledge"]').val('');
      $('input[name="Attitude"]').val('');
      $('input[name="Friendliness"]').val('');
      $("span").removeClass("redstar");
    });
    //On select Edit button remove the redstar class.
    $("#edit-choice-1").click(function(){
      $('input[name="Knowledge"]').val('');
      $('input[name="Attitude"]').val('');
      $('input[name="Friendliness"]').val('');
      $("span").removeClass("redstar");
    });
    //On click the knowledge star add and remove the class.
    //If click on whitestar then add redstar class or vice-versa.
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
    //On click the attitude star add and remove the class.
    //If click on whitestar then add redstar class or vice-versa.
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
    //On click the friendliness star add and remove the class.
    //If click on whitestar then add redstar class or vice-versa.
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
    //On select option from drop-down, selected value is pass to the text-field
    //of id = edit-name
    $('select[name="select"]').change(function() {
      $("#edit-name").val($(this).val());
    });
  });
  //This behaviour function is add the redstar class on the basis of previous values.
  //user can change the values.
  Drupal.behaviors.feedback = {
    attach: function (context, settings) {
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
  // Drupal.behaviors.views_exposed_form = {
  //   attach: function (context, settings) {
  //     $("#edit-name").val($('csv_select').val());
  //   }
  // };

}(jQuery));
