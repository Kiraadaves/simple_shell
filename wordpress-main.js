this file contains codes for my wordpress site modifications;
//main.js
(function ($) {
    "use strict";

    let decoder;

    function decodeHtmlBrowser(raw, asAttr = false) {
        if (!decoder) {
            decoder = document.createElement("div");
        }
        if (asAttr) {
            decoder.innerHTML = `<div foo="${raw.replace(/"/g, "&quot;")}">`;
            return decoder.children[0].getAttribute("foo");
        } else {
            decoder.innerHTML = raw;
            return decoder.textContent;
        }
    }

    function decodeSpanContent() {
        $(".search-input-label.category-name").each(function () {
            const rawText = $(this).html();
            const decodedText = decodeHtmlBrowser(rawText);
            $(this).html(decodedText);
        });
    }

    // Debounce function to limit how often decodeSpanContent is called
    function debounce(func, delay) {
        let timeout;
        return function (...args) {
            clearTimeout(timeout);
            timeout = setTimeout(() => func.apply(this, args), delay);
        };
    }

    const debouncedDecode = debounce(decodeSpanContent, 200); // 200ms delay

    $(document).ready(function () {
        decodeSpanContent(); // Initial decoding

        $(document).on('change', '.category-selector', function (e) {
            debouncedDecode(); // Debounced decoding on input change
            e.stopPropagation(); // Stop event from bubbling up
            e.preventDefault(); // Prevent any potential form submission
        });

        $(document).on('submit', 'form', function (e) {
            decodeSpanContent(); // Immediate decoding before form submission
            const submitter = e.originalEvent && e.originalEvent.submitter; // Get the element that triggered the submit
            const isSubmitButton = submitter && $(submitter).is('button[type="submit"], input[type="submit"]');
            const isApplyFiltersButton = $(submitter).hasClass('rtcl-filter-btn'); // Check if it's the Apply Filters button

            if (!isSubmitButton && !isApplyFiltersButton) {
                e.preventDefault(); // Block form submission
                console.log('Form submission blocked: submit button not clicked');
            } else {
                console.log('Form submitted via submit button');
            }
        });

        $(document).ajaxComplete(function (event, xhr, settings) {
            debouncedDecode(); // Debounced decoding for AJAX calls
        });

        $(document).on('click', '.reset-category', function () {
            debouncedDecode(); // Debounced decoding for resets
        });
    });
})(jQuery);

(function($) {
    "use strict";
    
    const sidebarSelector = 'aside.sidebar-widget-area.sidebar-listing-archive';
    const filterButtonSelector = '#classima-toggle-sidebar';

    // Hide the sidebar when clicking outside of it
    $(document).on('click', function(e) {
        const $target = $(e.target);

        // Ensure the click was not inside the sidebar or on the filter button
        if (
            !$target.closest(sidebarSelector).length && 
            !$target.closest(filterButtonSelector).length
        ) {
            $(sidebarSelector).hide(); // Hide the sidebar
        }
    });

    // Allow clicks inside the sidebar, including on 'Show More'
    $(document).on('click', sidebarSelector, function(e) {
        const $target = $(e.target);

        // Ensure sidebar stays visible when clicking inside
        if (!$target.closest('span.rtcl-more').length) {
            // Allow 'Show More' to propagate without hiding the sidebar
            e.stopPropagation();
        }
    });

})(jQuery);


(function ($) {
    "use strict";
	
	$(document).ready(function() {
    $('.ui-accordion .is-open').removeClass('is-open'); // Remove 'is-open' class initially
});

//select drop downs
jQuery(document).ready(function ($) {
	console.log("form")
    // Target the specific div containing the min and max inputs
    $('.form-group.row').each(function () {
        // Get references to the existing min and max input fields
        let minInput = $(this).find('input[name^="filters"][name$="[min]"]');
        let maxInput = $(this).find('input[name^="filters"][name$="[max]"]');

        // Create a select element for 'min'
        let minSelect = $('<select>')
            .attr({
                id: minInput.attr('id'),
                name: minInput.attr('name'),
                class: minInput.attr('class')
            })
            .append(
                $('<option>').val('').text('Min') // Placeholder option
            );

        // Populate the 'min' select with options
        for (let i = 1; i <= 10; i += 1) { // Example range
            minSelect.append($('<option>').val(i).text(i));
        }

        // Create a select element for 'max'
        let maxSelect = $('<select>')
            .attr({
                id: maxInput.attr('id'),
                name: maxInput.attr('name'),
                class: maxInput.attr('class')
            })
            .append(
                $('<option>').val('').text('Max') // Placeholder option
            );

        // Populate the 'max' select with options
        for (let i = 1; i <= 10; i += 1) { // Example range
            maxSelect.append($('<option>').val(i).text(i));
        }

        // Replace the input fields with the select elements
        minInput.closest('.ui-field').html(minSelect);
        maxInput.closest('.ui-field').html(maxSelect);
    });
});

	
	
	

    jQuery(document).ready(function ($) {
        /* Scroll to top */
        $('.scrollToTop').on('click', function () {
            $('html, body').animate({scrollTop: 0}, 800);
            return false;
        });
        $(window).scroll(function () {
            if ($(this).scrollTop() > 100) {
                $('.scrollToTop').fadeIn();
            } else {
                $('.scrollToTop').fadeOut();
            }
        });

        /* Bootstrap Tooltip */
        $('body').tooltip({
            selector: '[data-toggle=tooltip]'
        });

        /*  Mobile Menu */

        var a = $('.offscreen-navigation .menu');
        if (a.length) {
            a.children("li").addClass("menu-item-parent");
            a.find(".menu-item-has-children > a").on("click", function (e) {
                e.preventDefault();
                $(this).toggleClass("opened");
                var n = $(this).next(".sub-menu"),
                    s = $(this).closest(".menu-item-parent").find(".sub-menu");
                a.find(".sub-menu").not(s).slideUp(250).prev('a').removeClass('opened'), n.slideToggle(250)
            });
            a.find('.menu-item:not(.menu-item-has-children) > a').on('click', function (e) {
                $('.rt-slide-nav').slideUp();
                $('body').removeClass('slidemenuon');
            });
        }

        $('.sidebarBtn').on('click', function (e) {
            e.preventDefault();
            if ($('.rt-slide-nav').is(":visible")) {
                $('.rt-slide-nav').slideUp();
                $('body').removeClass('slidemenuon');
            } else {
                $('.rt-slide-nav').slideDown();
                $('body').addClass('slidemenuon');
            }

        });

        $('.classima-listing-cat-open-menu').on('click', function () {
            $('.rt-listing-cat-list-2 .listing-category-list').slideToggle();
        });

        $('.classima-MyAccount-open-menu').on('click', function () {
            $('.rtcl-MyAccount-mobile-navbar .rtcl-MyAccount-navigation').slideToggle();
        });

        /* Mega Menu */
        $('.site-header .main-navigation ul > li.mega-menu').each(function () {
            // total num of columns
            var items = $(this).find(' > ul.sub-menu > li').length;
            // screen width
            var bodyWidth = $('body').outerWidth();
            // main menu link width
            var parentLinkWidth = $(this).find(' > a').outerWidth();
            // main menu position from left
            var parentLinkpos = $(this).find(' > a').offset().left;

            var width = items * 240;
            var left = (width / 2) - (parentLinkWidth / 2);

            var linkleftWidth = parentLinkpos + (parentLinkWidth / 2);
            var linkRightWidth = bodyWidth - (parentLinkpos + parentLinkWidth);

            // exceeds left screen
            if ((width / 2) > linkleftWidth) {
                $(this).find(' > ul.sub-menu').css({
                    width: width + 'px',
                    right: 'inherit',
                    left: '-' + parentLinkpos + 'px'
                });
            }
            // exceeds right screen
            else if ((width / 2) > linkRightWidth) {
                $(this).find(' > ul.sub-menu').css({
                    width: width + 'px',
                    left: 'inherit',
                    right: '-' + linkRightWidth + 'px'
                });
            } else {
                $(this).find(' > ul.sub-menu').css({
                    width: width + 'px',
                    left: '-' + left + 'px'
                });
            }
        });

        /* Sticky Menu */

        if (ClassimaObj.hasStickyMenu == 1) {
            run_sticky_menu();
        }

        // Scripts needs loading inside content area
        rdtheme_content_ready_scripts();

        // resize autocomplete ui
        if ($(window).width() < 992) {
            var autocomplete_item = $(
                ".rtcl-widget-search-form .rtcl-autocomplete"
            );
            if ($.fn.autocomplete && autocomplete_item.length) {
                $.ui.autocomplete.prototype._resizeMenu = function () {
                    var ul = this.menu.element;
                    ul.outerWidth(this.element.closest('.form-group').outerWidth() - 35);
                }
            }
        }

    });

    // Window Load
    $(window).on('load', function () {

        // Scripts needs loading inside content area
        rdtheme_content_load_scripts();

        // Preloader
        $('#preloader').fadeOut('slow', function () {
            $(this).remove();
        });
    });

    // Elementor Frontend Load
    $(window).on('elementor/frontend/init', function () {
        if (elementorFrontend.isEditMode()) {
            elementorFrontend.hooks.addAction('frontend/element_ready/widget', function () {
                rdtheme_content_ready_scripts()
                rdtheme_content_load_scripts();
            });
        }
    });

    function rdtheme_content_ready_scripts() {

        /*---------------------------------------
          Background Parallax
          --------------------------------------- */
        if ($(".rt-parallax-bg-yes").length) {
            $(".rt-parallax-bg-yes").each(function () {
                var speed = $(this).data('speed');
                $(this).parallaxie({
                    speed: speed ? speed : 0.5,
                    offset: 0,
                });
            })
        }

        // Isotope
        if (typeof $.fn.isotope == 'function' && typeof $.fn.imagesLoaded == 'function') {

            // Blog Layout 2
            var $blogIsotopeContainer = $('.post-isotope');
            $blogIsotopeContainer.imagesLoaded(function () {
                $blogIsotopeContainer.isotope();
            });

            // Run 1st time
            var $isotopeContainer = $('.rt-el-isotope-container');
            $isotopeContainer.imagesLoaded(function () {
                $isotopeContainer.each(function () {
                    var $container = $(this).find('.rt-el-isotope-wrapper'),
                        filter = $(this).find('.rt-el-isotope-tab a.current').data('filter');
                    runIsotope($container, filter);
                });
            });

            // Run on click even
            $('.rt-el-isotope-tab a').on('click', function () {
                $(this).closest('.rt-el-isotope-tab').find('.current').removeClass('current');
                $(this).addClass('current');
                var $container = $(this).closest('.rt-el-isotope-container').find('.rt-el-isotope-wrapper'),
                    filter = $(this).attr('data-filter');
                runIsotope($container, filter);
                return false;
            });
        }

        /* Counter */
        if (typeof $.fn.counterUp == 'function') {
            $('.rt-el-counter .rt-counter-num').counterUp();
        }

        /* Zoom */
        if (typeof $.fn.zoom == 'function') {
            if (typeof rtcl_single_listing_params != 'undefined') {
                if (rtcl_single_listing_params.zoom_enabled) {
                    $('.classima-single-details .rtin-slider-box .rtcl-slider-item').zoom();
                }
            }
        }

        /* Listing Search Dropdown */
        $('.classima-listing-search-dropdown .dropdown-item').on('click', function () {
            var $parent = $(this).closest('.classima-listing-search-dropdown'),
                type = $(this).data('adtype'),
                text = $(this).text();

            $parent.find('input').val(type);
            $parent.find('button').text(text);
            $parent.dropdown('hide');

            return false;
        });

        /* Listing - Reveal Phone */
        $('.classima-phone-reveal').on('click', function () {
            if ($(this).hasClass('not-revealed')) {
                $(this).removeClass('not-revealed').addClass('revealed');
                var phone = $(this).data('phone');
                $(this).find('span').text(phone);
            }

            return false;
        });

        /* Listing - Toggle Filter */
        $('#classima-toggle-sidebar').on('click', function () {

            var $main = $('.sidebar-listing-archive');
            var display = $main.css('display');

            if (display == 'block') {
                $main.hide();
            }
            if (display == 'none') {
                $main.show();
            }

            return false;
        });

        $(".headerCategoriesMenu").on({
            mouseenter: function () {
                $('.headerCategoriesMenu__dropdown').css({
                    'opacity': '1',
                    'visibility': 'visible',
                    'transform': 'translateY(0px)',
                    '-webkit-transform': 'translateY(0px)'
                });
            },
            mouseleave: function () {
                $('.headerCategoriesMenu__dropdown').css({
                    'opacity': '0',
                    'visibility': 'hidden',
                    'transform': 'translateY(20px)',
                    '-webkit-transform': 'translateY(20px)'
                });
            }
        });

        $("#el_load_more").on("click", function (e) {
            e.preventDefault();

            var $this = $(this),
                $btnWrapper = $this.closest('.load-more-wrapper'),
                page = $btnWrapper.data('page'),
                display_options = $btnWrapper.data('options'),
                query = $btnWrapper.data('query'),
                layout = $btnWrapper.data('layout'),
                col_class = $btnWrapper.data('col-class'),
                total_pages = $btnWrapper.data('total-pages'),
                post_per_page = $btnWrapper.data('posts-per-page');

            $.ajax({
                // use the ajax object url
                type: "POST",
                url: ClassimaObj.ajax_url,
                data: {
                    action: "listing_load_more_ad",
                    offset: page * post_per_page,
                    layout: layout,
                    col_class: col_class,
                    post_per_page: post_per_page,
                    display: display_options,
                    queryArg: query
                },
                beforeSend: function () {
                    $btnWrapper.addClass('rt-loading');
                },
                success: function (data) {
                    // add the posts to the container and add to your page count
                    page++;
                    $btnWrapper.data('page', page);
                    $btnWrapper.closest('.rt-el-listing-grid').find('.row').append(data);
                    if (page > total_pages) {
                        $btnWrapper.hide();
                    }
                    $btnWrapper.removeClass('rt-loading');
                },
                error: function (data) {
                    // test to see what you get back on error
                    console.log(data);
                }
            });

        });

        /* Listing Mapview - Sidebar top */
        if ($('body').hasClass('mean-activated')) {
            var height = $('#meanmenu').outerHeight();
        } else {
            var height = $('#site-header').outerHeight();
        }

        if (ClassimaObj.hasAdminBar == 1) {
            height += $('#wpadminbar').outerHeight();
        }

        $('.listing-mapview-sidebar').css('top', height + 'px');

        /* Listing Mapview - Sticky Map */
        if (typeof StickySidebar == 'function') {
            var topSpacing = 0;

            if (ClassimaObj.hasStickyMenu == 1) {
                topSpacing += $('#site-header').outerHeight();
            }

            if (ClassimaObj.hasAdminBar == 1) {
                topSpacing += $('#wpadminbar').outerHeight();
            }
            if ($('.listing-mapview-map').length) {
                var sidebar = new StickySidebar('.listing-mapview-map', {
                    topSpacing: topSpacing,
                    minWidth: 1200,
                    containerSelector: '.listing-mapview-content-wrap',
                    innerWrapperSelector: '.rtcl-map-view'
                });
            }
        }
    }

    function rdtheme_content_load_scripts() {

        /* Animated text */
        if (typeof Typed == 'function' && $(window).width() > 1199.98) {
            $('.title-typejs').each(function (index, el) {
                var options = $(this).data('options');
                new Typed(this, options);
            });
        } else {
            $('.title-typejs').each(function (index, el) {
                var options = $(this).data('options');
                $(this).text(options.strings);
            });
        }
    }

    function run_sticky_menu() {

        var wrapperHtml = $('<div class="main-header-sticky-wrapper"></div>');
        var wrapperClass = '.main-header-sticky-wrapper';

        $('.main-header').clone(true).appendTo(wrapperHtml);
        $('body').append(wrapperHtml);

        var height = $(wrapperClass).outerHeight() + 30;

        $(wrapperClass).css('margin-top', '-' + height + 'px');

        $(window).scroll(function () {
            if ($(this).scrollTop() > 300) {
                $('body').addClass('rdthemeSticky');
            } else {
                $('body').removeClass('rdthemeSticky');
            }
        });
    }

    function runIsotope($container, filter) {
        $container.isotope({
            filter: filter,
            animationOptions: {
                duration: 750,
                easing: 'linear',
                queue: false
            }
        });
    }

})(jQuery);


/* Generate class based on container width */
(function ($) {
    "use strict";

    $(window).on('load resize', elementWidth);

    function elementWidth() {
        $('.elementwidth').each(function () {
            var $container = $(this),
                width = $container.outerWidth(),
                classes = $container.attr("class").split(' '); // get all class

            var classes1 = startWith(classes, 'elwidth'); // class starting with "elwidth"
            classes1 = classes1[0].split('-'); // "elwidth" classnames into array
            classes1.splice(0, 1); // remove 1st element "elwidth"

            var classes2 = startWith(classes, 'elmaxwidth'); // class starting with "elmaxwidth"
            classes2.forEach(function (el) {
                $container.removeClass(el);
            });

            classes1.forEach(function (el) {
                var maxWidth = parseInt(el);

                if (width <= maxWidth) {
                    $container.addClass('elmaxwidth-' + maxWidth);
                }
            });
        });
    }

    function startWith(item, stringName) {
        return $.grep(item, function (elem) {
            return elem.indexOf(stringName) == 0;
        });
    }

}(jQuery));


--------------------------------------------------------
Pluggin code edit for price range drop down

public function get_price_filter() {
    if ( ! empty( $this->instance['search_by_price'] ) ) {
        $filters    = ! empty( $_GET['filters'] ) ? $_GET['filters'] : []; /* phpcs:ignore WordPress.Security.NonceVerification.Recommended */
        $fMinValue  = ! empty( $filters['price']['min'] ) ? esc_attr( $filters['price']['min'] ) : null;
        $fMaxValue  = ! empty( $filters['price']['max'] ) ? esc_attr( $filters['price']['max'] ) : null;

        // Define options for the select fields.
        $price_options = apply_filters( 'rtcl_price_filter_options', [0, 50, 100, 200, 500, 1000, 2000, 5000, 10000] );

        // Generate options for the "min" select field.
        $min_options_html = '<option value="">' . esc_html__( 'Min', 'classified-listing' ) . '</option>';
        foreach ( $price_options as $price ) {
            $selected = ( $fMinValue !== null && (int) $fMinValue === $price ) ? ' selected' : '';
            $min_options_html .= sprintf(
                '<option value="%d"%s>%s</option>',
                esc_attr( $price ),
                $selected,
                esc_html( $price )
            );
        }

        // Generate options for the "max" select field.
        $max_options_html = '<option value="">' . esc_html__( 'Max', 'classified-listing' ) . '</option>';
        foreach ( $price_options as $price ) {
            $selected = ( $fMaxValue !== null && (int) $fMaxValue === $price ) ? ' selected' : '';
            $max_options_html .= sprintf(
                '<option value="%d"%s>%s</option>',
                esc_attr( $price ),
                $selected,
                esc_html( $price )
            );
        }

        $field_html = sprintf(
            '<div class="form-group">
                <div class="price-container">
                    <div class="row">
                        <div class="col-md-6 col-6">
                            <select name="filters[price][min]" class="form-control">%s</select>
                        </div>
                        <div class="col-md-6 col-6">
                            <select name="filters[price][max]" class="form-control">%s</select>
                        </div>
                    </div>
                </div>
            </div>',
            $min_options_html,
            $max_options_html
        );

        return sprintf(
            '<div class="rtcl-price-filter ui-accordion-item is-open">
                <a class="ui-accordion-title">
                    <span>%s</span>
                    <span class="ui-accordion-icon rtcl-icon rtcl-icon-anchor"></span>
                </a>
                <div class="ui-accordion-content">%s</div>
            </div>',
            apply_filters( 'rtcl_widget_filter_price_title', esc_html__( "Price Range", "classified-listing" ) ),
            $field_html
        );
    }
}
