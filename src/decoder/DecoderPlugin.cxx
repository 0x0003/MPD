// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The Music Player Daemon Project

#include "DecoderPlugin.hxx"
#include "util/StringCompare.hxx"
#include "util/StringUtil.hxx"

#include <algorithm>
#include <cassert>

bool
DecoderPlugin::SupportsUri(const std::string_view uri) const noexcept
{
	if (protocols != nullptr) {
		const auto p = protocols();
		return std::any_of(p.begin(), p.end(), [uri](const auto &schema)
			{ return StringStartsWithIgnoreCase(uri, schema); } );
	}

	return false;
}

[[gnu::pure]]
static bool
SetContains(const auto &set, std::string_view key) noexcept
{
	/* the sets contain only lower-case suffixes; fold the key so
	   matching is case-insensitive, like the static suffix lists
	   ("*.MP3" must be handled like "*.mp3") */
	const std::string lower = ToLowerCaseASCII(key);

#ifdef ANDROID
	/* the libc++ version in Android NDK r25c doesn't implement
	   std::set::contains() */
	return set.find(lower) != set.end();
#else
	return set.contains(lower);
#endif
}

bool
DecoderPlugin::SupportsSuffix(std::string_view suffix) const noexcept
{
	return (suffixes != nullptr &&
		StringArrayContainsCase(suffixes, suffix)) ||
		(suffixes_function != nullptr &&
		 SetContains(suffixes_function(), suffix));
}

bool
DecoderPlugin::SupportsMimeType(std::string_view mime_type) const noexcept
{
	return mime_types != nullptr &&
		StringArrayContainsCase(mime_types, mime_type);
}
