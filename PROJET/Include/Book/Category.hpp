#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		PlayerHue			= 1 << 1,
		Pickup				= 1 << 2,
	};
}

#endif // BOOK_CATEGORY_HPP
