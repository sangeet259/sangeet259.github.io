---
layout: page
title: Tags
subtitle: Interested in something specific? Find it here.
permalink: /tags
---

{% if site.tags %}
<div class="well">
	{% for tag in site.tags %}
	{% assign mtag = tag|first %}
<a style="color: #404040;" href="#{{mtag}}"><h4 style="display: inline">#{{mtag}}</h4></a>&nbsp;&nbsp;
	{% endfor %}
</div>
	{% for tag in site.tags %}
	{% assign mytag = tag | first %}
<h3 id="{{mytag}}">{{mytag | capitalize}}</h3>
		{% for post in site.tags[mytag] %}
<div class="well">
<a style="color: #404040;" href="{{post.url | prepend: site.baseurl }}">
	<h4 class="post-title">{{post.title}}</h4>
</a>
    Posted on {{ post.date | date: "%B %-d, %Y" }}
</div>
		{% endfor %}
<br>
   {% endfor %}
{% endif %}