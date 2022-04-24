package com.github.wjinlei.springbootblog.service;

import com.github.wjinlei.springbootblog.dao.UserMapper;
import com.github.wjinlei.springbootblog.entity.User;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;

@ExtendWith(MockitoExtension.class) /* 为这个测试启用Mockito扩展 */
class UserServiceTest {
    @Mock
    BCryptPasswordEncoder mockBCryptPasswordEncoder; /* 假的BCryptPasswordEncoder */
    @Mock
    UserMapper mockUserMapper; /* 假的UserMapper */
    @InjectMocks
    UserService userService; /* 真实的UserService,并为他注入上面的Mock依赖 */

    @Test
    public void testRegisterUser() {
        /* 当mockBCryptPasswordEncoder.encode("plaintext")的时候,让它返回"ciphertext",模拟加密过程 */
        Mockito.when(mockBCryptPasswordEncoder.encode("plaintext")).thenReturn("ciphertext");
        userService.registerUser("test", "plaintext"); /* 测试这个方法 */
        /* 我希望调用registerUser的时候,传递给mockUserMapper的值是"test"和"ciphertext" */
        Mockito.verify(mockUserMapper).registerUser("test", "ciphertext"); /* 验证一下mockUserMapper以什么方式被调用了 */
    }

    @Test
    public void testSelectUserByUsername() {
        userService.selectUserByUsername("test");
        Mockito.verify(mockUserMapper).selectUserByUsername("test"); /* 验证一下mockUserMapper是否收到的值是"test" */
    }

    @Test
    public void testLoadUserByUsernameThrowsUsernameNotFoundException() {
        /* 当调用mockUserMapper.selectUserByUsername("test"),模拟让它返回null */
//        Mockito.when(mockUserMapper.selectUserByUsername("test")).thenReturn(null);
        /* 上面的实际是多余的,因为你不对它配置的时候,它默认就是返回null */

        /* 断言一下,当执行userService.loadUserByUsername("test")的时候会抛出UsernameNotFoundException异常 */
        Assertions.assertThrows(UsernameNotFoundException.class,
                () -> userService.loadUserByUsername("test"));
    }

    @Test
    public void testLoadUserByUsernameReturnUserDetail() {
        /* 当调用mockUserMapper.selectUserByUsername("test")模拟让它返回一个User对象 */
        Mockito.when(mockUserMapper.selectUserByUsername("test"))
                .thenReturn(new User("test", "ciphertext"));
        UserDetails userDetails = userService.loadUserByUsername("test"); /* 调用实际的逻辑 */
        /* 验证返回的结果是否符合预期 */
        Assertions.assertEquals("test", userDetails.getUsername());
        Assertions.assertEquals("ciphertext", userDetails.getPassword());
    }
}
