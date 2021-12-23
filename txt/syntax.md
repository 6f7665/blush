!cat:syntax:
!title:Syntax:
!sub:docs:
!tag:syntax,documentation:
!start:
<p>
# Syntax
Blush has it's own syntax, every command starts with ! at the start of the line and ends with : followed by the argument.
The first part of the file is reserved blush specific generation settings.
These settings are for tagging and categorization (indexing).
Once the start command is given the indexing will stop.

## Blush indexing syntax
These settings are used in the beginning of the file to categorize the file so that it can be linked to from other files/web-pages.  
  
` !cat:[arg]: `, adds page to the category [arg]  
` !title:[arg]: `, if this page is linked to from another page the link will appear as [arg]  
` !sub:[arg]: `, adds page to the sub category [arg], this will make the page appear in the menu  
` !tag:[arg]: `, adds page to the tag [arg]  
` !start: `, ends the indexing  

## Blush document syntax
These commands are used inside the document as a way to conveniently link pages together, import images and make blog pages.  
  
` !impsub:[arg] `, links every page that belongs to the sub-category [arg] in a list  
` !imptag:[arg] `, links every page that belongs to the tag [arg] in a list  
~~ ` !impblog:[arg]:[n] `, creates a blog with the files in folder [arg] with [n] entries per page~~  
~~ ` !impimg:[arg]:[title] `, creates img element with the image [arg] and title [title]~~  

## Markdown

The markdown support is not very extensive, but more functionalities will be added as time moves on.
If you need other functionalies please use a different markdown processor, or contribute to the project by adding them!  
  
double space at the end of a line creates a &#60;br&#62; tag.    
` \ `, escape character  
` # `, header, number of consecutive hashtags increases header level  
`` ` ``, begins codeblock, if multiple \` are used the code will have to be exited with that amount  
` *italic* `, makes italic appear as *italic*  
` **bold** `, makes bold appear as **bold**  
` ~~strike~~ `, makes strike appear as ~~strike~~  
` __underline__ `, makes underline appear __underlined__  
` _**bold italic**_ `, makes text  _**bold and italic**_  
</p>
