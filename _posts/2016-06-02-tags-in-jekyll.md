---
layout: post
title: Implementing tags in Jekyll
permalink: /tags-in-jekyll
tags: ["jekyll","liquid"]
subtitle: Implementing tags in Jekyll using Liquid template engine
---

Hello there. So, after experimenting a little around with Jekyll, I found some really interesting features in it. As said in the documentation, Jekyll is "blog-aware" and tags are a very important part of any blog.

So, to experiment with the Liquid template engine, I decided to take a very simple theme which does not have features like "Tags" built-in. The theme I'm using is <a href="https://github.com/daattali/beautiful-jekyll" target="_blank">Beautiful Jekyll.</a> This is a very simple and elegant theme and since it had Bootstrap bundled, I chose it for faster prototyping of design elements. 

Now, Jekyll has Liquid support, and Liquid supports a variety of variables in it. For example, the Page variables are referred to by using variables like <code>page.tags</code> and site variables using <code>site.data</code>. Every page has Front matter written in YAML, and you can include tags like this- 
<code>
	tags: ["tag1", "tag2", "tag3"]
</code>

### How do we get tags and the posts ?
Coming back to the topic, whenever you give some tags to a page, it automatically gets added to <code>site.tags</code> along with the list of posts. Let me show you the code in the <kbd>tags.md</kbd> page and then explain it line by line.

<h4>tags.md</h4>
{% highlight liquid %}
	{% raw %}
{% if site.tags %}
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
{% endif %}{% endraw %}
{% endhighlight %}

Now, the explanation. We first search for a property <code>site.tags</code>. This is a variable which has key, value pairs. For every object in it, we use the line <code>assign mytag = tag|first</code> to get the key (in our case, the tags). The value to the key is a list of all the posts under the tag. We iterate through the posts and use the properties <code>post.url</code>, <code>post.title</code> and <code>post.date</code> to display all the posts under the tag.
Now, our tag page is ready. Now, optionally, you could also include your post tags in every post which redirects to the <kbd>tags.md</kbd> page. I leave it as an exercise for you.

Confused? Refer to <a target="_blank" href="https://github.com/rohitrango/rohitrango.github.io/commit/e9ee7cb8f5bd8fd1b52f1314b22f76f2bc37b44a">this</a> commit to see how I implemented the tags in my blog.

Happy coding!!