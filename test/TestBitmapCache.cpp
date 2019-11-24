/**********************************************************************************
 * MIT License
 * 
 * Copyright (c) 2018 Antoine Beauchamp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *********************************************************************************/

#include "TestBitmapCache.h"
#include "BitmapCache.h"
#include "win32_utils.h"
#include "rapidassist/testing.h"

namespace shellanything { namespace test
{
  HBITMAP LoadTestBitmap(int index)
  {
    HICON hIconLarge = NULL;
    HICON hIconSmall = NULL;

    UINT numIconLoaded = ExtractIconEx( "c:\\windows\\system32\\shell32.dll", index, &hIconLarge, &hIconSmall, 1 );

    //Convert the icon to a bitmap (with invisible background)
    SIZE icon_size = win32_utils::GetIconSize(hIconLarge);
    HBITMAP hBitmap = win32_utils::CopyAsBitmap(hIconLarge, icon_size.cx, icon_size.cy);

    //Remove the invisible background and replace by red color
    COLORREF background_color = RGB(255,0,255); //pink
    win32_utils::FillTransparentPixels(hBitmap, background_color);

    DestroyIcon(hIconLarge);
    DestroyIcon(hIconSmall);

    return hBitmap;
  }

  HBITMAP LoadTestBitmap(const std::string & filename, int index)
  {
    HICON hIconLarge = NULL;
    HICON hIconSmall = NULL;

    UINT numIconLoaded = ExtractIconEx( filename.c_str(), index, &hIconLarge, &hIconSmall, 1 );

    //Convert the icon to a bitmap (with invisible background)
    SIZE icon_size = win32_utils::GetIconSize(hIconLarge);
    HBITMAP hBitmap = win32_utils::CopyAsBitmap(hIconLarge, icon_size.cx, icon_size.cy);

    //Remove the invisible background and replace by red color
    COLORREF background_color = RGB(255,0,255); //pink
    win32_utils::FillTransparentPixels(hBitmap, background_color);

    DestroyIcon(hIconLarge);
    DestroyIcon(hIconSmall);

    return hBitmap;
  }


  //--------------------------------------------------------------------------------------------------
  void TestBitmapCache::SetUp()
  {
  }
  //--------------------------------------------------------------------------------------------------
  void TestBitmapCache::TearDown()
  {
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestBitmapCache, testAdd)
  {
    BitmapCache cache;

    std::string filename = "c:\\windows\\system32\\shell32.dll";
    int index = 0;

    HBITMAP hBitmap = LoadTestBitmap(0);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap );

    //add
    cache.add_handle(filename, index, hBitmap);

    //assert it is added
    HBITMAP hDuplicate = cache.find_handle(filename, index);
    ASSERT_EQ( hBitmap, hDuplicate );

    DeleteObject(hBitmap);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestBitmapCache, testFindHandle)
  {
    BitmapCache cache;

    std::string filename = "c:\\windows\\system32\\shell32.dll";
    int index = 0;

    HBITMAP hBitmap = LoadTestBitmap(0);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap );

    //add
    cache.add_handle(filename, index, hBitmap);

    //assert it is added
    HBITMAP hDuplicate1 = cache.find_handle(filename, index);
    ASSERT_EQ( hBitmap, hDuplicate1 );

    int count = cache.get_usage(filename, index);
    ASSERT_EQ( 1, count );

    //assert usage increases for every find_handle() call
    HBITMAP hDuplicate2 = cache.find_handle(filename, index);
    HBITMAP hDuplicate3 = cache.find_handle(filename, index);
    HBITMAP hDuplicate4 = cache.find_handle(filename, index);
    count = cache.get_usage(filename, index);
    ASSERT_EQ( 4, count );

    DeleteObject(hBitmap);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestBitmapCache, testResetCounters)
  {
    BitmapCache cache;

    std::string filename = "c:\\windows\\system32\\shell32.dll";
    int index = 0;

    HBITMAP hBitmap = LoadTestBitmap(0);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap );

    //add
    cache.add_handle(filename, index, hBitmap);

    //increase usage
    HBITMAP hDuplicate1 = cache.find_handle(filename, index);
    HBITMAP hDuplicate2 = cache.find_handle(filename, index);
    HBITMAP hDuplicate3 = cache.find_handle(filename, index);
    HBITMAP hDuplicate4 = cache.find_handle(filename, index);
    int count = cache.get_usage(filename, index);
    ASSERT_EQ( 4, count );

    cache.reset_counters();

    //get usage again
    count = cache.get_usage(filename, index);
    ASSERT_EQ( 0, count ); //assert unused

    DeleteObject(hBitmap);
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestBitmapCache, testClearAndDestroy)
  {
    BitmapCache cache;

    std::string filename = "c:\\windows\\system32\\shell32.dll";
    int index = 0;

    HBITMAP hBitmap = LoadTestBitmap(0);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap );

    //add
    cache.add_handle(filename, index, hBitmap);

    //act
    cache.reset_counters(); //make sure that all bitmap in the cache will be destroyed
    cache.clear_and_destroy();

    //get usage
    int count = cache.get_usage(filename, index);
    ASSERT_EQ( -1, count ); //assert not found

    //try to destroy in main scope
    BOOL destroyed = DeleteObject(hBitmap);
    ASSERT_FALSE( destroyed );
  }
  //--------------------------------------------------------------------------------------------------
  TEST_F(TestBitmapCache, testDestroyOldHandles)
  {
    BitmapCache cache;

    std::string filename = "c:\\windows\\system32\\shell32.dll";

    HBITMAP hBitmap0 = LoadTestBitmap(0);
    HBITMAP hBitmap1 = LoadTestBitmap(1);
    HBITMAP hBitmap2 = LoadTestBitmap(2);
    HBITMAP hBitmap3 = LoadTestBitmap(3);
    HBITMAP hBitmap4 = LoadTestBitmap(3);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap0 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap1 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap2 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap3 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hBitmap4 );

    //add
    cache.add_handle(filename, 0, hBitmap0);
    cache.add_handle(filename, 1, hBitmap1);
    cache.add_handle(filename, 2, hBitmap2);
    cache.add_handle(filename, 3, hBitmap3);
    cache.add_handle(filename, 4, hBitmap4);

    //inserse usage of the first 3
    HBITMAP hFound0 = cache.find_handle(filename, 0);
    HBITMAP hFound1 = cache.find_handle(filename, 1);
    HBITMAP hFound2 = cache.find_handle(filename, 2);
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hFound0 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hFound1 );
    ASSERT_NE( BitmapCache::INVALID_BITMAP_HANDLE, hFound2 );

    //act
    int num_destroyed = cache.destroy_old_handles();
    ASSERT_EQ( 2, num_destroyed ); //hBitmap3 and hBitmap4

    //assert some are destroyed, some not
    BOOL destroyed0 = DeleteObject(hBitmap0);
    BOOL destroyed1 = DeleteObject(hBitmap1);
    BOOL destroyed2 = DeleteObject(hBitmap2);
    BOOL destroyed3 = DeleteObject(hBitmap3);
    BOOL destroyed4 = DeleteObject(hBitmap4);
    ASSERT_TRUE ( destroyed0 ); //destroyed at this call
    ASSERT_TRUE ( destroyed1 ); //destroyed at this call
    ASSERT_TRUE ( destroyed2 ); //destroyed at this call
    ASSERT_FALSE( destroyed3 ); //destroyed previouly by the cache
    ASSERT_FALSE( destroyed4 ); //destroyed previouly by the cache
  }
  //--------------------------------------------------------------------------------------------------

} //namespace test
} //namespace shellanything
