/**
 * @file
 * Required functions to use the Mobile Switch administration.
 */

Drupal.behaviors.mobileSwitch = function(context) {
 // Basic settings form; Hide/show "Administration usage"
 if ($('#edit-mobile-switch-mobile-theme').val() == 'none') {
  $('#edit-mobile-switch-admin-usage-wrapper').hide();
 }
 else {
  $('#edit-mobile-switch-admin-usage-wrapper').show();
 }
 $('#edit-mobile-switch-mobile-theme').click(function() {
  if ($(this).val() == 'none') {
   $('#edit-mobile-switch-admin-usage-wrapper').hide();
  }
  else {
   $('#edit-mobile-switch-admin-usage-wrapper').show();
  }
 });
 // Advanced form; Hide/show preventing strings textarea.
 if ($('#edit-mobile-switch-prevent-devices').val() == 0) {
  $('#edit-mobile-switch-prevent-devices-strings-wrapper').hide();
 }
 else {
  $('#edit-mobile-switch-prevent-devices-strings-wrapper').show();
 }
 $('#edit-mobile-switch-prevent-devices').click(function() {
  if ($(this).val() == '0') {
   $('#edit-mobile-switch-prevent-devices-strings-wrapper').hide();
  }
  else {
   $('#edit-mobile-switch-prevent-devices-strings-wrapper').show();
  }
 });
 // Development form; Hide/show "Advanced developer modus settings" and
 // uncheck "Display user agent".
 if ($('#edit-mobile-switch-developer').val() == 0) {
  $('#edit-mobile-switch-advanced-developer').hide();
 }
 else {
  $('#edit-mobile-switch-advanced-developer').show();
 }
 $('#edit-mobile-switch-developer').click(function() {
  if ($(this).val() == 0) {
   togggleUa();
   $('#edit-mobile-switch-advanced-developer').hide();
  }
  else {
   $('#edit-mobile-switch-advanced-developer').show();
  }
 });
 // Uncheck "Display user agent" and "Display browscap informations".
 function togggleUa() {
  if ($('#edit-mobile-switch-display-useragent').is(':checked')) {
   $('#edit-mobile-switch-display-useragent').attr('checked', false);
  }
  if ($('#edit-mobile-switch-display-browscapinfo').is(':checked')) {
   $('#edit-mobile-switch-display-browscapinfo').attr('checked', false);
  }
 }
};
