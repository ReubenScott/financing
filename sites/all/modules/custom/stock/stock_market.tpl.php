<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

  echo $result[0]; echo "<br/>";
  echo $result[1]; echo "<br/>";
  echo $result[2]; echo "<br/>";
  echo $result[3]; echo "<br/>";
?>


<table>
 <tr><td><img src='<?php echo $min_src ; ?>'  /></td></tr>
 <tr><td><img src='<?php echo $rkx_src ; ?>'  /></td></tr>
</table>


<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<table>
            <form name="searchStock" method="get" action="" >
            <tr><td>股票代码：<input name="scode" type="text" />股票名称：<input name="sname" type="text" /></td></tr>
            <tr><td>
             
             
            <font style="font-size:14px">股票代码</font>  <INPUT name=code  id=code  onkeyup="//value=value.replace(/[^\d{2}]/,'');" autocomplete="off"  style="border:1px solid #BCBCBC;line-height:26px;height:26px;font-size:14px;width: 250px;color:#D06700;background-color: #F7FBFF;padding-right: 2px;padding-left: 2px " >
             
            <input name="" type="submit" value="立即查询" style="height:28px;font-size:14px;font-weight:normal;width:100px;line-height: 24px;margin-right: 10px; "/>
             
            </td></tr>
            </form>
<script type="text/javascript" src=" http://js.18vr.com/js/SuggestFramework.js"></script>
            <script type="text/javascript"> 
            function LoadStockJs() {
window.suggestStock_top = new Suggest("code", "", [" http://js.18vr.com/js/astock.js"], ["astock_suggest"], StockSuggestConfiguration, null, [200, 800, 0.95, "solid", "#EEE", "#FFF", 3, 3, 0.2, "#000", "#444", "#e5ebfb", false]);
            }
            if(LoadStockJs) LoadStockJs();
            </script>
            
            </table>

  
  
