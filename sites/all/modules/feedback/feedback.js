(function ($) {
  Drupal.behaviors.feedback = {
    attach: function (context, settings) {
      // Your Javascript code goes here
       alert(Drupal.settings.feedback.tax_rate);

    }
  };
}(jQuery));
